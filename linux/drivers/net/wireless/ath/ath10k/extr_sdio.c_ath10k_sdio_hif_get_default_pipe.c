#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ath10k_sdio_hif_get_default_pipe(struct ath10k *ar,
					     u8 *ul_pipe, u8 *dl_pipe)
{
	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio hif get default pipe\n");

	/* HTC ctrl ep (SVC id 1) always has eid (and pipe_id in our
	 * case) == 0
	 */
	*ul_pipe = 0;
	*dl_pipe = 0;
}