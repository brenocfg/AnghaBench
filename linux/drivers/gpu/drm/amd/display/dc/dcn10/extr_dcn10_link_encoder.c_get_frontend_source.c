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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGA ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGB ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGC ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGD ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGE ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGF ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_DIGG ; 
 int /*<<< orphan*/  DCN10_DIG_FE_SOURCE_SELECT_INVALID ; 
#define  ENGINE_ID_DIGA 134 
#define  ENGINE_ID_DIGB 133 
#define  ENGINE_ID_DIGC 132 
#define  ENGINE_ID_DIGD 131 
#define  ENGINE_ID_DIGE 130 
#define  ENGINE_ID_DIGF 129 
#define  ENGINE_ID_DIGG 128 

__attribute__((used)) static uint8_t get_frontend_source(
	enum engine_id engine)
{
	switch (engine) {
	case ENGINE_ID_DIGA:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGA;
	case ENGINE_ID_DIGB:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGB;
	case ENGINE_ID_DIGC:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGC;
	case ENGINE_ID_DIGD:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGD;
	case ENGINE_ID_DIGE:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGE;
	case ENGINE_ID_DIGF:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGF;
	case ENGINE_ID_DIGG:
		return DCN10_DIG_FE_SOURCE_SELECT_DIGG;
	default:
		ASSERT_CRITICAL(false);
		return DCN10_DIG_FE_SOURCE_SELECT_INVALID;
	}
}