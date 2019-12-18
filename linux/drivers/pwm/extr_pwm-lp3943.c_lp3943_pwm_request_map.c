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
struct lp3943_pwm_map {int* output; int num_outputs; } ;
struct lp3943_pwm {struct lp3943* lp3943; struct lp3943_platform_data* pdata; } ;
struct lp3943_platform_data {TYPE_1__** pwms; } ;
struct lp3943 {int /*<<< orphan*/  pin_used; } ;
struct TYPE_2__ {int* output; int num_outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct lp3943_pwm_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct lp3943_pwm_map*) ; 
 struct lp3943_pwm_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lp3943_pwm_map *
lp3943_pwm_request_map(struct lp3943_pwm *lp3943_pwm, int hwpwm)
{
	struct lp3943_platform_data *pdata = lp3943_pwm->pdata;
	struct lp3943 *lp3943 = lp3943_pwm->lp3943;
	struct lp3943_pwm_map *pwm_map;
	int i, offset;

	pwm_map = kzalloc(sizeof(*pwm_map), GFP_KERNEL);
	if (!pwm_map)
		return ERR_PTR(-ENOMEM);

	pwm_map->output = pdata->pwms[hwpwm]->output;
	pwm_map->num_outputs = pdata->pwms[hwpwm]->num_outputs;

	for (i = 0; i < pwm_map->num_outputs; i++) {
		offset = pwm_map->output[i];

		/* Return an error if the pin is already assigned */
		if (test_and_set_bit(offset, &lp3943->pin_used)) {
			kfree(pwm_map);
			return ERR_PTR(-EBUSY);
		}
	}

	return pwm_map;
}