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
typedef  int /*<<< orphan*/  u32 ;
struct sun8i_mixer {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ is_de3; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE2_BLD_BASE ; 
 int /*<<< orphan*/  DE3_BLD_BASE ; 

__attribute__((used)) static inline u32
sun8i_blender_base(struct sun8i_mixer *mixer)
{
	return mixer->cfg->is_de3 ? DE3_BLD_BASE : DE2_BLD_BASE;
}