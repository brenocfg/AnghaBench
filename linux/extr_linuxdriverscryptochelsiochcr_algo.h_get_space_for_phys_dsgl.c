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
typedef  unsigned int u16 ;

/* Variables and functions */
 unsigned int PHYSDSGL_MAX_LEN_SIZE ; 

__attribute__((used)) static inline u16 get_space_for_phys_dsgl(unsigned int sgl_entr)
{
	/* len field size + addr field size */
	return ((sgl_entr >> 3) + ((sgl_entr % 8) ?
				   1 : 0)) * PHYSDSGL_MAX_LEN_SIZE +
		(sgl_entr << 3) + ((sgl_entr % 2 ? 1 : 0) << 3);
}