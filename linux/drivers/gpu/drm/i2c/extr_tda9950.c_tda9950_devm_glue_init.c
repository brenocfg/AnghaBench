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
struct tda9950_glue {int (* init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int devm_add_action (struct device*,int /*<<< orphan*/  (*) (struct tda9950_glue*),struct tda9950_glue*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda9950_devm_glue_exit (struct tda9950_glue*) ; 

__attribute__((used)) static int tda9950_devm_glue_init(struct device *dev, struct tda9950_glue *glue)
{
	int ret;

	if (glue && glue->init) {
		ret = glue->init(glue->data);
		if (ret)
			return ret;
	}

	ret = devm_add_action(dev, tda9950_devm_glue_exit, glue);
	if (ret)
		tda9950_devm_glue_exit(glue);

	return ret;
}