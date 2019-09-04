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
struct s3c24xx_dma_chan {int /*<<< orphan*/  vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct s3c24xx_dma_chan* to_s3c24xx_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c24xx_dma_synchronize(struct dma_chan *chan)
{
	struct s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);

	vchan_synchronize(&s3cchan->vc);
}