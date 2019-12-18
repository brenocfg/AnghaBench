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
struct rbsp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int rbsp_write_uev (struct rbsp*,unsigned int*) ; 

__attribute__((used)) static int rbsp_write_sev(struct rbsp *rbsp, int *value)
{
	unsigned int tmp;

	if (!value)
		return -EINVAL;

	if (*value > 0)
		tmp = (2 * (*value)) | 1;
	else
		tmp = -2 * (*value);

	return rbsp_write_uev(rbsp, &tmp);
}