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
struct hvsi_struct {int flags; } ;

/* Variables and functions */
 int HVSI_CONSOLE ; 

__attribute__((used)) static inline int is_console(struct hvsi_struct *hp)
{
	return hp->flags & HVSI_CONSOLE;
}