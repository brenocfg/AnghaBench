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
struct drxd_state {int app_env_default; scalar_t__ operation_mode; int app_env_diversity; scalar_t__ type_A; int /*<<< orphan*/  m_InitCE; } ;
typedef  enum app_env { ____Placeholder_app_env } app_env ;

/* Variables and functions */
 int APPENV_MOBILE ; 
 int APPENV_PORTABLE ; 
 int APPENV_STATIC ; 
 int /*<<< orphan*/  B_CE_REG_COMM_EXEC__A ; 
 int /*<<< orphan*/  CE_REG_TAPSET__A ; 
 scalar_t__ OM_DVBT_Diversity_End ; 
 scalar_t__ OM_DVBT_Diversity_Front ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int WriteTable (struct drxd_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int InitCE(struct drxd_state *state)
{
	int status;
	enum app_env AppEnv = state->app_env_default;

	do {
		status = WriteTable(state, state->m_InitCE);
		if (status < 0)
			break;

		if (state->operation_mode == OM_DVBT_Diversity_Front ||
		    state->operation_mode == OM_DVBT_Diversity_End) {
			AppEnv = state->app_env_diversity;
		}
		if (AppEnv == APPENV_STATIC) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0000, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_PORTABLE) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0001, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_MOBILE && state->type_A) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0002, 0);
			if (status < 0)
				break;
		} else if (AppEnv == APPENV_MOBILE && !state->type_A) {
			status = Write16(state, CE_REG_TAPSET__A, 0x0006, 0);
			if (status < 0)
				break;
		}

		/* start ce */
		status = Write16(state, B_CE_REG_COMM_EXEC__A, 0x0001, 0);
		if (status < 0)
			break;
	} while (0);
	return status;
}