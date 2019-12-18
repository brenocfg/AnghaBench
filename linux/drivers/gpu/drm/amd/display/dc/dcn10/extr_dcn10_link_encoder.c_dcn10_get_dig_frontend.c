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
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;
typedef  int int32_t ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGA 134 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGB 133 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGC 132 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGD 131 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGE 130 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGF 129 
#define  DCN10_DIG_FE_SOURCE_SELECT_DIGG 128 
 int /*<<< orphan*/  DIG_BE_CNTL ; 
 int /*<<< orphan*/  DIG_FE_SOURCE_SELECT ; 
 int ENGINE_ID_DIGA ; 
 int ENGINE_ID_DIGB ; 
 int ENGINE_ID_DIGC ; 
 int ENGINE_ID_DIGD ; 
 int ENGINE_ID_DIGE ; 
 int ENGINE_ID_DIGF ; 
 int ENGINE_ID_DIGG ; 
 int ENGINE_ID_UNKNOWN ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

unsigned int dcn10_get_dig_frontend(struct link_encoder *enc)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	int32_t value;
	enum engine_id result;

	REG_GET(DIG_BE_CNTL, DIG_FE_SOURCE_SELECT, &value);

	switch (value) {
	case DCN10_DIG_FE_SOURCE_SELECT_DIGA:
		result = ENGINE_ID_DIGA;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGB:
		result = ENGINE_ID_DIGB;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGC:
		result = ENGINE_ID_DIGC;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGD:
		result = ENGINE_ID_DIGD;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGE:
		result = ENGINE_ID_DIGE;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGF:
		result = ENGINE_ID_DIGF;
		break;
	case DCN10_DIG_FE_SOURCE_SELECT_DIGG:
		result = ENGINE_ID_DIGG;
		break;
	default:
		// invalid source select DIG
		ASSERT(false);
		result = ENGINE_ID_UNKNOWN;
	}

	return result;

}