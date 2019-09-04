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
typedef  int u32 ;
struct s3c24xx_txd {int width; } ;
struct s3c24xx_dma_phy {scalar_t__ base; } ;
struct s3c24xx_dma_chan {struct s3c24xx_txd* at; struct s3c24xx_dma_phy* phy; } ;

/* Variables and functions */
 scalar_t__ S3C24XX_DSTAT ; 
 int S3C24XX_DSTAT_CURRTC_MASK ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u32 s3c24xx_dma_getbytes_chan(struct s3c24xx_dma_chan *s3cchan)
{
	struct s3c24xx_dma_phy *phy = s3cchan->phy;
	struct s3c24xx_txd *txd = s3cchan->at;
	u32 tc = readl(phy->base + S3C24XX_DSTAT) & S3C24XX_DSTAT_CURRTC_MASK;

	return tc * txd->width;
}