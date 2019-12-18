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
struct CHIPSTATE {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int tda9874a_AMSEL ; 
 int tda9874a_ESP ; 
 int tda9874a_GCONR ; 
 int tda9874a_NCONR ; 
 int tda9874a_SIF ; 
 int tda9874a_STD ; 
 int tda9874a_mode ; 
 int /*<<< orphan*/  tda9874a_modelist ; 
 int /*<<< orphan*/  tda9874a_setup (struct CHIPSTATE*) ; 

__attribute__((used)) static int tda9874a_initialize(struct CHIPSTATE *chip)
{
	if (tda9874a_SIF > 2)
		tda9874a_SIF = 1;
	if (tda9874a_STD >= ARRAY_SIZE(tda9874a_modelist))
		tda9874a_STD = 0;
	if(tda9874a_AMSEL > 1)
		tda9874a_AMSEL = 0;

	if(tda9874a_SIF == 1)
		tda9874a_GCONR = 0xc0;	/* sound IF input 1 */
	else
		tda9874a_GCONR = 0xc1;	/* sound IF input 2 */

	tda9874a_ESP = tda9874a_STD;
	tda9874a_mode = (tda9874a_STD < 5) ? 0 : 1;

	if(tda9874a_AMSEL == 0)
		tda9874a_NCONR = 0x01; /* auto-mute: analog mono input */
	else
		tda9874a_NCONR = 0x05; /* auto-mute: 1st carrier FM or AM */

	tda9874a_setup(chip);
	return 0;
}