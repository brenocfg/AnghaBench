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

/* Variables and functions */
 double dml_max (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  dml_max4 (double,double,double,double) ; 

__attribute__((used)) static inline double dml_max5(double a, double b, double c, double d, double e)
{
	return dml_max(dml_max4(a, b, c, d), e);
}