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
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;
typedef  enum audio_dto_source { ____Placeholder_audio_dto_source } audio_dto_source ;

/* Variables and functions */
#define  CONTROLLER_ID_D0 133 
#define  CONTROLLER_ID_D1 132 
#define  CONTROLLER_ID_D2 131 
#define  CONTROLLER_ID_D3 130 
#define  CONTROLLER_ID_D4 129 
#define  CONTROLLER_ID_D5 128 
 int DTO_SOURCE_ID0 ; 
 int DTO_SOURCE_ID1 ; 
 int DTO_SOURCE_ID2 ; 
 int DTO_SOURCE_ID3 ; 
 int DTO_SOURCE_ID4 ; 
 int DTO_SOURCE_ID5 ; 
 int DTO_SOURCE_UNKNOWN ; 

__attribute__((used)) static enum audio_dto_source translate_to_dto_source(enum controller_id crtc_id)
{
	switch (crtc_id) {
	case CONTROLLER_ID_D0:
		return DTO_SOURCE_ID0;
	case CONTROLLER_ID_D1:
		return DTO_SOURCE_ID1;
	case CONTROLLER_ID_D2:
		return DTO_SOURCE_ID2;
	case CONTROLLER_ID_D3:
		return DTO_SOURCE_ID3;
	case CONTROLLER_ID_D4:
		return DTO_SOURCE_ID4;
	case CONTROLLER_ID_D5:
		return DTO_SOURCE_ID5;
	default:
		return DTO_SOURCE_UNKNOWN;
	}
}