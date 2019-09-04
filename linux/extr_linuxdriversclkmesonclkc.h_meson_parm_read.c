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
struct regmap {int dummy; } ;
struct parm {int /*<<< orphan*/  shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg_off; } ;

/* Variables and functions */
 unsigned int PARM_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline unsigned int meson_parm_read(struct regmap *map, struct parm *p)
{
	unsigned int val;

	regmap_read(map, p->reg_off, &val);
	return PARM_GET(p->width, p->shift, val);
}