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
struct siw_cep {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __siw_cep_dealloc ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kref_read (int /*<<< orphan*/ *) ; 

void siw_cep_put(struct siw_cep *cep)
{
	WARN_ON(kref_read(&cep->ref) < 1);
	kref_put(&cep->ref, __siw_cep_dealloc);
}