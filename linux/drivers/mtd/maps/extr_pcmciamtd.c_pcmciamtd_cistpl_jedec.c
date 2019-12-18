#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuple_t ;
struct pcmcia_device {int dummy; } ;
struct TYPE_6__ {int nid; TYPE_1__* id; } ;
typedef  TYPE_2__ cistpl_jedec_t ;
struct TYPE_7__ {TYPE_2__ jedec; } ;
typedef  TYPE_3__ cisparse_t ;
struct TYPE_5__ {int /*<<< orphan*/  info; int /*<<< orphan*/  mfr; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  pcmcia_parse_tuple (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmciamtd_cistpl_jedec(struct pcmcia_device *p_dev,
				tuple_t *tuple,
				void *priv_data)
{
	cisparse_t parse;
	int i;

	if (!pcmcia_parse_tuple(tuple, &parse)) {
		cistpl_jedec_t *t = &parse.jedec;
		for (i = 0; i < t->nid; i++)
			pr_debug("JEDEC: 0x%02x 0x%02x\n",
			      t->id[i].mfr, t->id[i].info);
	}
	return -ENOSPC;
}