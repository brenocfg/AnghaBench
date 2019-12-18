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
struct rbsp {TYPE_1__* ops; scalar_t__ error; } ;
struct TYPE_2__ {scalar_t__ (* rbsp_bit ) (struct rbsp*,int*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct rbsp*,int*) ; 

__attribute__((used)) static inline void rbsp_bit(struct rbsp *rbsp, int *value)
{
	if (rbsp->error)
		return;
	rbsp->error = rbsp->ops->rbsp_bit(rbsp, value);
}