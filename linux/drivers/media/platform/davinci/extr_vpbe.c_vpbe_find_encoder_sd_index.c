#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  module_name; } ;
struct vpbe_config {int num_ext_encoders; TYPE_3__* ext_encoders; TYPE_2__ venc; TYPE_1__* outputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  module_name; } ;
struct TYPE_4__ {char* subdev_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_find_encoder_sd_index(struct vpbe_config *cfg,
			     int index)
{
	char *encoder_name = cfg->outputs[index].subdev_name;
	int i;

	/* Venc is always first	*/
	if (!strcmp(encoder_name, cfg->venc.module_name))
		return 0;

	for (i = 0; i < cfg->num_ext_encoders; i++) {
		if (!strcmp(encoder_name,
		     cfg->ext_encoders[i].module_name))
			return i+1;
	}

	return -EINVAL;
}