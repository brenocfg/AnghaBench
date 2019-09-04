#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xor_cb {TYPE_2__* ops; int /*<<< orphan*/  cblal; int /*<<< orphan*/  cblah; int /*<<< orphan*/  cbtal; int /*<<< orphan*/  cbtah; int /*<<< orphan*/  cbs; int /*<<< orphan*/  cbbc; int /*<<< orphan*/  cbc; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct dma_cdb {int /*<<< orphan*/  sg3l; int /*<<< orphan*/  sg3u; int /*<<< orphan*/  sg2l; int /*<<< orphan*/  sg2u; int /*<<< orphan*/  sg1l; int /*<<< orphan*/  sg1u; int /*<<< orphan*/  cnt; int /*<<< orphan*/  opc; int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  l; int /*<<< orphan*/  h; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void print_cb(struct ppc440spe_adma_chan *chan, void *block)
{
	struct dma_cdb *cdb;
	struct xor_cb *cb;
	int i;

	switch (chan->device->id) {
	case 0:
	case 1:
		cdb = block;

		pr_debug("CDB at %p [%d]:\n"
			"\t attr 0x%02x opc 0x%02x cnt 0x%08x\n"
			"\t sg1u 0x%08x sg1l 0x%08x\n"
			"\t sg2u 0x%08x sg2l 0x%08x\n"
			"\t sg3u 0x%08x sg3l 0x%08x\n",
			cdb, chan->device->id,
			cdb->attr, cdb->opc, le32_to_cpu(cdb->cnt),
			le32_to_cpu(cdb->sg1u), le32_to_cpu(cdb->sg1l),
			le32_to_cpu(cdb->sg2u), le32_to_cpu(cdb->sg2l),
			le32_to_cpu(cdb->sg3u), le32_to_cpu(cdb->sg3l)
		);
		break;
	case 2:
		cb = block;

		pr_debug("CB at %p [%d]:\n"
			"\t cbc 0x%08x cbbc 0x%08x cbs 0x%08x\n"
			"\t cbtah 0x%08x cbtal 0x%08x\n"
			"\t cblah 0x%08x cblal 0x%08x\n",
			cb, chan->device->id,
			cb->cbc, cb->cbbc, cb->cbs,
			cb->cbtah, cb->cbtal,
			cb->cblah, cb->cblal);
		for (i = 0; i < 16; i++) {
			if (i && !cb->ops[i].h && !cb->ops[i].l)
				continue;
			pr_debug("\t ops[%2d]: h 0x%08x l 0x%08x\n",
				i, cb->ops[i].h, cb->ops[i].l);
		}
		break;
	}
}