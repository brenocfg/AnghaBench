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
struct sdio_func {int dummy; } ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cis_tpl_funce_list ; 
 int cis_tpl_parse (struct mmc_card*,struct sdio_func*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int cistpl_funce(struct mmc_card *card, struct sdio_func *func,
			const unsigned char *buf, unsigned size)
{
	if (size < 1)
		return -EINVAL;

	return cis_tpl_parse(card, func, "CISTPL_FUNCE",
			     cis_tpl_funce_list,
			     ARRAY_SIZE(cis_tpl_funce_list),
			     buf[0], buf, size);
}