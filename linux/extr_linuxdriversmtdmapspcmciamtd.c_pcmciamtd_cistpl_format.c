#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuple_t ;
struct pcmcia_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; int /*<<< orphan*/  edc; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cistpl_format_t ;
struct TYPE_5__ {TYPE_1__ format; } ;
typedef  TYPE_2__ cisparse_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  pcmcia_parse_tuple (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmciamtd_cistpl_format(struct pcmcia_device *p_dev,
				tuple_t *tuple,
				void *priv_data)
{
	cisparse_t parse;

	if (!pcmcia_parse_tuple(tuple, &parse)) {
		cistpl_format_t *t = &parse.format;
		(void)t; /* Shut up, gcc */
		pr_debug("Format type: %u, Error Detection: %u, offset = %u, length =%u\n",
			t->type, t->edc, t->offset, t->length);
	}
	return -ENOSPC;
}