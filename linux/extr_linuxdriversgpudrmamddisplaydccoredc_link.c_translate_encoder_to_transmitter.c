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
struct graphics_object_id {int id; int /*<<< orphan*/  enum_id; } ;
typedef  enum transmitter { ____Placeholder_transmitter } transmitter ;

/* Variables and functions */
#define  ENCODER_ID_EXTERNAL_NUTMEG 135 
#define  ENCODER_ID_EXTERNAL_TRAVIS 134 
#define  ENCODER_ID_INTERNAL_UNIPHY 133 
#define  ENCODER_ID_INTERNAL_UNIPHY1 132 
#define  ENCODER_ID_INTERNAL_UNIPHY2 131 
#define  ENCODER_ID_INTERNAL_UNIPHY3 130 
#define  ENUM_ID_1 129 
#define  ENUM_ID_2 128 
 int TRANSMITTER_NUTMEG_CRT ; 
 int TRANSMITTER_TRAVIS_CRT ; 
 int TRANSMITTER_TRAVIS_LCD ; 
 int TRANSMITTER_UNIPHY_A ; 
 int TRANSMITTER_UNIPHY_B ; 
 int TRANSMITTER_UNIPHY_C ; 
 int TRANSMITTER_UNIPHY_D ; 
 int TRANSMITTER_UNIPHY_E ; 
 int TRANSMITTER_UNIPHY_F ; 
 int TRANSMITTER_UNIPHY_G ; 
 int TRANSMITTER_UNKNOWN ; 

__attribute__((used)) static enum transmitter translate_encoder_to_transmitter(
	struct graphics_object_id encoder)
{
	switch (encoder.id) {
	case ENCODER_ID_INTERNAL_UNIPHY:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_UNIPHY_A;
		case ENUM_ID_2:
			return TRANSMITTER_UNIPHY_B;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	case ENCODER_ID_INTERNAL_UNIPHY1:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_UNIPHY_C;
		case ENUM_ID_2:
			return TRANSMITTER_UNIPHY_D;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	case ENCODER_ID_INTERNAL_UNIPHY2:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_UNIPHY_E;
		case ENUM_ID_2:
			return TRANSMITTER_UNIPHY_F;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	case ENCODER_ID_INTERNAL_UNIPHY3:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_UNIPHY_G;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	case ENCODER_ID_EXTERNAL_NUTMEG:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_NUTMEG_CRT;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	case ENCODER_ID_EXTERNAL_TRAVIS:
		switch (encoder.enum_id) {
		case ENUM_ID_1:
			return TRANSMITTER_TRAVIS_CRT;
		case ENUM_ID_2:
			return TRANSMITTER_TRAVIS_LCD;
		default:
			return TRANSMITTER_UNKNOWN;
		}
	break;
	default:
		return TRANSMITTER_UNKNOWN;
	}
}