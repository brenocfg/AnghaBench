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
struct io_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_mapping_free (struct io_mapping*) ; 

__attribute__((used)) static inline void
fbmem_fini(struct io_mapping *fb)
{
	io_mapping_free(fb);
}