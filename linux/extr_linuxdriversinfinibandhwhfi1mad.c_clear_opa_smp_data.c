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
struct opa_smp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* opa_get_smp_data (struct opa_smp*) ; 
 size_t opa_get_smp_data_size (struct opa_smp*) ; 

__attribute__((used)) static inline void clear_opa_smp_data(struct opa_smp *smp)
{
	void *data = opa_get_smp_data(smp);
	size_t size = opa_get_smp_data_size(smp);

	memset(data, 0, size);
}