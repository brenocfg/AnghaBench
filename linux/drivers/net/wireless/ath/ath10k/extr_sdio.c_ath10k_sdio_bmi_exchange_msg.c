#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  htc_addr; } ;
struct ath10k_sdio {void* bmi_buf; TYPE_1__ mbox_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ath10k_sdio_bmi_credits (struct ath10k*) ; 
 int ath10k_sdio_bmi_get_rx_lookahead (struct ath10k*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int ath10k_sdio_read (struct ath10k*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int ath10k_sdio_write (struct ath10k*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_bmi_exchange_msg(struct ath10k *ar,
					void *req, u32 req_len,
					void *resp, u32 *resp_len)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 addr;
	int ret;

	if (req) {
		ret = ath10k_sdio_bmi_credits(ar);
		if (ret)
			return ret;

		addr = ar_sdio->mbox_info.htc_addr;

		memcpy(ar_sdio->bmi_buf, req, req_len);
		ret = ath10k_sdio_write(ar, addr, ar_sdio->bmi_buf, req_len);
		if (ret) {
			ath10k_warn(ar,
				    "unable to send the bmi data to the device: %d\n",
				    ret);
			return ret;
		}
	}

	if (!resp || !resp_len)
		/* No response expected */
		return 0;

	/* During normal bootup, small reads may be required.
	 * Rather than issue an HIF Read and then wait as the Target
	 * adds successive bytes to the FIFO, we wait here until
	 * we know that response data is available.
	 *
	 * This allows us to cleanly timeout on an unexpected
	 * Target failure rather than risk problems at the HIF level.
	 * In particular, this avoids SDIO timeouts and possibly garbage
	 * data on some host controllers.  And on an interconnect
	 * such as Compact Flash (as well as some SDIO masters) which
	 * does not provide any indication on data timeout, it avoids
	 * a potential hang or garbage response.
	 *
	 * Synchronization is more difficult for reads larger than the
	 * size of the MBOX FIFO (128B), because the Target is unable
	 * to push the 129th byte of data until AFTER the Host posts an
	 * HIF Read and removes some FIFO data.  So for large reads the
	 * Host proceeds to post an HIF Read BEFORE all the data is
	 * actually available to read.  Fortunately, large BMI reads do
	 * not occur in practice -- they're supported for debug/development.
	 *
	 * So Host/Target BMI synchronization is divided into these cases:
	 *  CASE 1: length < 4
	 *        Should not happen
	 *
	 *  CASE 2: 4 <= length <= 128
	 *        Wait for first 4 bytes to be in FIFO
	 *        If CONSERVATIVE_BMI_READ is enabled, also wait for
	 *        a BMI command credit, which indicates that the ENTIRE
	 *        response is available in the the FIFO
	 *
	 *  CASE 3: length > 128
	 *        Wait for the first 4 bytes to be in FIFO
	 *
	 * For most uses, a small timeout should be sufficient and we will
	 * usually see a response quickly; but there may be some unusual
	 * (debug) cases of BMI_EXECUTE where we want an larger timeout.
	 * For now, we use an unbounded busy loop while waiting for
	 * BMI_EXECUTE.
	 *
	 * If BMI_EXECUTE ever needs to support longer-latency execution,
	 * especially in production, this code needs to be enhanced to sleep
	 * and yield.  Also note that BMI_COMMUNICATION_TIMEOUT is currently
	 * a function of Host processor speed.
	 */
	ret = ath10k_sdio_bmi_get_rx_lookahead(ar);
	if (ret)
		return ret;

	/* We always read from the start of the mbox address */
	addr = ar_sdio->mbox_info.htc_addr;
	ret = ath10k_sdio_read(ar, addr, ar_sdio->bmi_buf, *resp_len);
	if (ret) {
		ath10k_warn(ar,
			    "unable to read the bmi data from the device: %d\n",
			    ret);
		return ret;
	}

	memcpy(resp, ar_sdio->bmi_buf, *resp_len);

	return 0;
}