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
struct nvkm_clk {scalar_t__ allow_reclock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 int nvkm_clk_ustate_update (struct nvkm_clk*,long) ; 
 scalar_t__ strncasecmpz (char const*,char*,int) ; 

__attribute__((used)) static int
nvkm_clk_nstate(struct nvkm_clk *clk, const char *mode, int arglen)
{
	int ret = 1;

	if (clk->allow_reclock && !strncasecmpz(mode, "auto", arglen))
		return -2;

	if (strncasecmpz(mode, "disabled", arglen)) {
		char save = mode[arglen];
		long v;

		((char *)mode)[arglen] = '\0';
		if (!kstrtol(mode, 0, &v)) {
			ret = nvkm_clk_ustate_update(clk, v);
			if (ret < 0)
				ret = 1;
		}
		((char *)mode)[arglen] = save;
	}

	return ret - 2;
}