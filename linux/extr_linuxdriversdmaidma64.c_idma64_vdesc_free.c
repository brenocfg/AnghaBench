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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct idma64_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idma64_desc_free (struct idma64_chan*,int /*<<< orphan*/ ) ; 
 struct idma64_chan* to_idma64_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_idma64_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void idma64_vdesc_free(struct virt_dma_desc *vdesc)
{
	struct idma64_chan *idma64c = to_idma64_chan(vdesc->tx.chan);

	idma64_desc_free(idma64c, to_idma64_desc(vdesc));
}