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
struct stm32_rproc {TYPE_1__* mb; } ;
struct rproc {int /*<<< orphan*/  dev; struct stm32_rproc* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char const*) ; 
 int /*<<< orphan*/  strlen (unsigned char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_rproc_mbox_idx(struct rproc *rproc, const unsigned char *name)
{
	struct stm32_rproc *ddata = rproc->priv;
	int i;

	for (i = 0; i < ARRAY_SIZE(ddata->mb); i++) {
		if (!strncmp(ddata->mb[i].name, name, strlen(name)))
			return i;
	}
	dev_err(&rproc->dev, "mailbox %s not found\n", name);

	return -EINVAL;
}