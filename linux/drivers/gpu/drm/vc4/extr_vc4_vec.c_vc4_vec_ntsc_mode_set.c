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
struct vc4_vec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_CONFIG0 ; 
 int VEC_CONFIG0_NTSC_STD ; 
 int VEC_CONFIG0_PDEN ; 
 int /*<<< orphan*/  VEC_CONFIG1 ; 
 int VEC_CONFIG1_C_CVBS_CVBS ; 
 int /*<<< orphan*/  VEC_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vc4_vec_ntsc_mode_set(struct vc4_vec *vec)
{
	VEC_WRITE(VEC_CONFIG0, VEC_CONFIG0_NTSC_STD | VEC_CONFIG0_PDEN);
	VEC_WRITE(VEC_CONFIG1, VEC_CONFIG1_C_CVBS_CVBS);
}