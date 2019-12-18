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
typedef  int /*<<< orphan*/  u32 ;
struct atmel_hlcdc_plane {int /*<<< orphan*/  layer; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_hlcdc_layer_write_cfg (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
atmel_hlcdc_plane_scaler_set_phicoeff(struct atmel_hlcdc_plane *plane,
				      const u32 *coeff_tab, int size,
				      unsigned int cfg_offs)
{
	int i;

	for (i = 0; i < size; i++)
		atmel_hlcdc_layer_write_cfg(&plane->layer, cfg_offs + i,
					    coeff_tab[i]);
}