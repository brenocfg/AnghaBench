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
typedef  int u32 ;
struct iss_device {int dummy; } ;
typedef  enum iss_mem_resources { ____Placeholder_iss_mem_resources } iss_mem_resources ;

/* Variables and functions */
 int iss_reg_read (struct iss_device*,int,int) ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int,int,int) ; 

__attribute__((used)) static inline
void iss_reg_set(struct iss_device *iss, enum iss_mem_resources res,
		 u32 offset, u32 set)
{
	u32 v = iss_reg_read(iss, res, offset);

	iss_reg_write(iss, res, offset, v | set);
}