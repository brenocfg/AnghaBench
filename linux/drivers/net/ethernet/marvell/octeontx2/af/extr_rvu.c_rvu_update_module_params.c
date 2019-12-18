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
struct rvu {int /*<<< orphan*/  mkex_pfl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKEX_NAME_LEN ; 
 char const* mkex_profile ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rvu_update_module_params(struct rvu *rvu)
{
	const char *default_pfl_name = "default";

	strscpy(rvu->mkex_pfl_name,
		mkex_profile ? mkex_profile : default_pfl_name, MKEX_NAME_LEN);
}