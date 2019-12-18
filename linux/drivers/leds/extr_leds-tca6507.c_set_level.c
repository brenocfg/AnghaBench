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
struct tca6507_chip {TYPE_1__* bank; } ;
struct TYPE_2__ {int level; } ;

/* Variables and functions */
#define  BANK0 130 
#define  BANK1 129 
#define  MASTER 128 
 int /*<<< orphan*/  TCA6507_MASTER_INTENSITY ; 
 int /*<<< orphan*/  TCA6507_MAX_INTENSITY ; 
 int /*<<< orphan*/  set_code (struct tca6507_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void set_level(struct tca6507_chip *tca, int bank, int level)
{
	switch (bank) {
	case BANK0:
	case BANK1:
		set_code(tca, TCA6507_MAX_INTENSITY, bank, level);
		break;
	case MASTER:
		set_code(tca, TCA6507_MASTER_INTENSITY, 0, level);
		break;
	}
	tca->bank[bank].level = level;
}