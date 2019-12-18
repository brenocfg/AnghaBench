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
struct nct6775_data {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ nct6775 ; 
 int /*<<< orphan*/  nct6775_write_fan_div (struct nct6775_data*,int) ; 

__attribute__((used)) static void nct6775_write_fan_div_common(struct nct6775_data *data, int nr)
{
	if (data->kind == nct6775)
		nct6775_write_fan_div(data, nr);
}