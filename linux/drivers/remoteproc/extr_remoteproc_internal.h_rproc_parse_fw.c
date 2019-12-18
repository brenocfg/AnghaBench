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
struct rproc {TYPE_1__* ops; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int (* parse_fw ) (struct rproc*,struct firmware const*) ;} ;

/* Variables and functions */
 int stub1 (struct rproc*,struct firmware const*) ; 

__attribute__((used)) static inline int rproc_parse_fw(struct rproc *rproc, const struct firmware *fw)
{
	if (rproc->ops->parse_fw)
		return rproc->ops->parse_fw(rproc, fw);

	return 0;
}