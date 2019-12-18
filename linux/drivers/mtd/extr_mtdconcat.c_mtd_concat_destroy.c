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
struct mtd_info {int dummy; } ;
struct TYPE_2__ {struct mtd_concat* eraseregions; scalar_t__ numeraseregions; } ;
struct mtd_concat {TYPE_1__ mtd; } ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int /*<<< orphan*/  kfree (struct mtd_concat*) ; 

void mtd_concat_destroy(struct mtd_info *mtd)
{
	struct mtd_concat *concat = CONCAT(mtd);
	if (concat->mtd.numeraseregions)
		kfree(concat->mtd.eraseregions);
	kfree(concat);
}