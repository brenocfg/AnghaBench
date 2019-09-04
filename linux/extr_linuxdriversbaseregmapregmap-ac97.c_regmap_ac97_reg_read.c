#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ac97 {TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {unsigned int (* read ) (struct snd_ac97*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct snd_ac97*,unsigned int) ; 

__attribute__((used)) static int regmap_ac97_reg_read(void *context, unsigned int reg,
	unsigned int *val)
{
	struct snd_ac97 *ac97 = context;

	*val = ac97->bus->ops->read(ac97, reg);

	return 0;
}