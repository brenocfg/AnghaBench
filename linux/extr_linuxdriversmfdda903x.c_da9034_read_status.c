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
typedef  int uint8_t ;
struct da903x_chip {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9034_STATUS_A ; 
 int __da903x_reads (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int da9034_read_status(struct da903x_chip *chip, unsigned int *status)
{
	uint8_t v[2] = {0, 0};
	int ret = 0;

	ret = __da903x_reads(chip->client, DA9034_STATUS_A, 2, v);
	if (ret)
		return ret;

	*status = (v[1] << 8) | v[0];
	return 0;
}