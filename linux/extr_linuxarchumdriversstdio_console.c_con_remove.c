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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int line_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  vts ; 

__attribute__((used)) static int con_remove(int n, char **error_out)
{
	return line_remove(vts, ARRAY_SIZE(vts), n, error_out);
}