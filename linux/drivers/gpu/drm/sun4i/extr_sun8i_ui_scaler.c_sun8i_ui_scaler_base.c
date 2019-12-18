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
typedef  scalar_t__ u32 ;
struct sun8i_mixer {TYPE_1__* cfg; } ;
struct TYPE_2__ {int vi_num; scalar_t__ is_de3; } ;

/* Variables and functions */
 int DE2_UI_SCALER_UNIT_SIZE ; 
 scalar_t__ DE2_VI_SCALER_UNIT_BASE ; 
 int DE2_VI_SCALER_UNIT_SIZE ; 
 int DE3_UI_SCALER_UNIT_SIZE ; 
 scalar_t__ DE3_VI_SCALER_UNIT_BASE ; 
 int DE3_VI_SCALER_UNIT_SIZE ; 

__attribute__((used)) static u32 sun8i_ui_scaler_base(struct sun8i_mixer *mixer, int channel)
{
	int vi_num = mixer->cfg->vi_num;

	if (mixer->cfg->is_de3)
		return DE3_VI_SCALER_UNIT_BASE +
		       DE3_VI_SCALER_UNIT_SIZE * vi_num +
		       DE3_UI_SCALER_UNIT_SIZE * (channel - vi_num);
	else
		return DE2_VI_SCALER_UNIT_BASE +
		       DE2_VI_SCALER_UNIT_SIZE * vi_num +
		       DE2_UI_SCALER_UNIT_SIZE * (channel - vi_num);
}