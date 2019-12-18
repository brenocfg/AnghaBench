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
struct radeon_encoder_atom_dig {int coherent_mode; int dig_encoder; int linkb; } ;
struct radeon_encoder {int encoder_enum; } ;

/* Variables and functions */
 int ENUM_ID_MASK ; 
 int ENUM_ID_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct radeon_encoder_atom_dig* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct radeon_encoder_atom_dig *
radeon_atombios_set_dig_info(struct radeon_encoder *radeon_encoder)
{
	int encoder_enum = (radeon_encoder->encoder_enum & ENUM_ID_MASK) >> ENUM_ID_SHIFT;
	struct radeon_encoder_atom_dig *dig = kzalloc(sizeof(struct radeon_encoder_atom_dig), GFP_KERNEL);

	if (!dig)
		return NULL;

	/* coherent mode by default */
	dig->coherent_mode = true;
	dig->dig_encoder = -1;

	if (encoder_enum == 2)
		dig->linkb = true;
	else
		dig->linkb = false;

	return dig;
}