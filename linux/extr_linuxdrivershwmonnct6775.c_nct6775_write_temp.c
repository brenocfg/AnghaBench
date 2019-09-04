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
typedef  int u16 ;
struct nct6775_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_word_sized (struct nct6775_data*,int) ; 
 int nct6775_write_value (struct nct6775_data*,int,int) ; 

__attribute__((used)) static int nct6775_write_temp(struct nct6775_data *data, u16 reg, u16 value)
{
	if (!is_word_sized(data, reg))
		value >>= 8;
	return nct6775_write_value(data, reg, value);
}