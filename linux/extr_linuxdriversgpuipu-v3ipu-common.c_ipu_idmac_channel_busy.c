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
struct ipu_soc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_CHA_BUSY (unsigned int) ; 
 int idma_mask (unsigned int) ; 
 int ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 

bool ipu_idmac_channel_busy(struct ipu_soc *ipu, unsigned int chno)
{
	return (ipu_idmac_read(ipu, IDMAC_CHA_BUSY(chno)) & idma_mask(chno));
}