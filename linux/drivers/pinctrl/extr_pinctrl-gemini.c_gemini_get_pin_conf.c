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
struct gemini_pmx {int nconfs; struct gemini_pin_conf* confs; } ;
struct gemini_pin_conf {unsigned int pin; } ;

/* Variables and functions */

__attribute__((used)) static const struct gemini_pin_conf *gemini_get_pin_conf(struct gemini_pmx *pmx,
							 unsigned int pin)
{
	const struct gemini_pin_conf *retconf;
	int i;

	for (i = 0; i < pmx->nconfs; i++) {
		retconf = &pmx->confs[i];
		if (retconf->pin == pin)
			return retconf;
	}
	return NULL;
}