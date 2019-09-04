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
struct ipuv3_channel {unsigned int num; struct ipu_soc* ipu; } ;
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CHA_CUR_BUF (unsigned int) ; 
 int /*<<< orphan*/  idma_mask (unsigned int) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ipu_idmac_reset_current_buffer(struct ipuv3_channel *channel)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned int chno = channel->num;

	ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_CUR_BUF(chno));
}