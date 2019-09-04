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
typedef  int u8 ;
struct btmrvl_sdio_card {TYPE_1__* reg; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_intstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int DN_LD_HOST_INT_STATUS ; 
 int UP_LD_HOST_INT_STATUS ; 
 int sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int btmrvl_sdio_write_to_clear(struct btmrvl_sdio_card *card, u8 *ireg)
{
	int ret;

	*ireg = sdio_readb(card->func, card->reg->host_intstatus, &ret);
	if (ret) {
		BT_ERR("sdio_readb: read int status failed: %d", ret);
		return ret;
	}

	if (*ireg) {
		/*
		 * DN_LD_HOST_INT_STATUS and/or UP_LD_HOST_INT_STATUS
		 * Clear the interrupt status register and re-enable the
		 * interrupt.
		 */
		BT_DBG("int_status = 0x%x", *ireg);

		sdio_writeb(card->func, ~(*ireg) & (DN_LD_HOST_INT_STATUS |
						    UP_LD_HOST_INT_STATUS),
			    card->reg->host_intstatus, &ret);
		if (ret) {
			BT_ERR("sdio_writeb: clear int status failed: %d", ret);
			return ret;
		}
	}

	return 0;
}