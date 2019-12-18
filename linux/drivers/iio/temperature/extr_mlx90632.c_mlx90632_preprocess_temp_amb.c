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
typedef  long long s64 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 long long MLX90632_REF_3 ; 
 long long div64_s64 (long long,long long) ; 

__attribute__((used)) static s64 mlx90632_preprocess_temp_amb(s16 ambient_new_raw,
					s16 ambient_old_raw, s16 Gb)
{
	s64 VR_Ta, kGb, tmp;

	kGb = ((s64)Gb * 1000LL) >> 10ULL;
	VR_Ta = (s64)ambient_old_raw * 1000000LL +
		kGb * div64_s64(((s64)ambient_new_raw * 1000LL),
			(MLX90632_REF_3));
	tmp = div64_s64(
			 div64_s64(((s64)ambient_new_raw * 1000000000000LL),
				   (MLX90632_REF_3)), VR_Ta);
	return div64_s64(tmp << 19ULL, 1000LL);
}