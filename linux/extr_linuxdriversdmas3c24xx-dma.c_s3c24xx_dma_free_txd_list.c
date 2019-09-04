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
struct s3c24xx_dma_engine {int dummy; } ;
struct s3c24xx_dma_chan {int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c24xx_dma_free_txd_list(struct s3c24xx_dma_engine *s3cdma,
				struct s3c24xx_dma_chan *s3cchan)
{
	LIST_HEAD(head);

	vchan_get_all_descriptors(&s3cchan->vc, &head);
	vchan_dma_desc_free_list(&s3cchan->vc, &head);
}