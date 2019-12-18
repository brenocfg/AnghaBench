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
typedef  scalar_t__ u32 ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 scalar_t__ fbmem_peek (struct io_mapping*,scalar_t__) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline bool
fbmem_readback(struct io_mapping *fb, u32 off, u32 val)
{
	fbmem_poke(fb, off, val);
	return val == fbmem_peek(fb, off);
}