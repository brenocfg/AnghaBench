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
typedef  int /*<<< orphan*/  u8 ;
struct mpu3050 {int lpf; int /*<<< orphan*/  divisor; } ;
typedef  enum mpu3050_lpf { ____Placeholder_mpu3050_lpf } mpu3050_lpf ;

/* Variables and functions */
 int LPF_256_HZ_NOLPF ; 
 int mpu3050_start_sampling (struct mpu3050*) ; 

__attribute__((used)) static int mpu3050_set_8khz_samplerate(struct mpu3050 *mpu3050)
{
	int ret;
	u8 divisor;
	enum mpu3050_lpf lpf;

	lpf = mpu3050->lpf;
	divisor = mpu3050->divisor;

	mpu3050->lpf = LPF_256_HZ_NOLPF; /* 8 kHz base frequency */
	mpu3050->divisor = 0; /* Divide by 1 */
	ret = mpu3050_start_sampling(mpu3050);

	mpu3050->lpf = lpf;
	mpu3050->divisor = divisor;

	return ret;
}