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
typedef  int /*<<< orphan*/  moduleid_t ;

/* Variables and functions */
 unsigned char L1_BRICKTYPE_C ; 
#define  L1_BRICKTYPE_GA 135 
 unsigned char L1_BRICKTYPE_I ; 
#define  L1_BRICKTYPE_IA 134 
#define  L1_BRICKTYPE_IX 133 
#define  L1_BRICKTYPE_OPUS_TIO 132 
 unsigned char L1_BRICKTYPE_P ; 
#define  L1_BRICKTYPE_PA 131 
#define  L1_BRICKTYPE_PE 130 
#define  L1_BRICKTYPE_PX 129 
#define  L1_BRICKTYPE_SA 128 
 int MODULE_FORMAT_BRIEF ; 
 int MODULE_FORMAT_LCD ; 
 int MODULE_FORMAT_LONG ; 
 int MODULE_GET_BPOS (int /*<<< orphan*/ ) ; 
 unsigned char MODULE_GET_BTCHAR (int /*<<< orphan*/ ) ; 
 int MODULE_GET_RACK (int /*<<< orphan*/ ) ; 
 void* RACK_GET_CLASS (int) ; 
 void* RACK_GET_GROUP (int) ; 
 void* RACK_GET_NUM (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
format_module_id(char *buffer, moduleid_t m, int fmt)
{
	int rack, position;
	unsigned char brickchar;

	rack = MODULE_GET_RACK(m);
	brickchar = MODULE_GET_BTCHAR(m);

	/* Be sure we use the same brick type character as displayed
	 * on the brick's LCD
	 */
	switch (brickchar) 
	{
	case L1_BRICKTYPE_GA:
	case L1_BRICKTYPE_OPUS_TIO:
		brickchar = L1_BRICKTYPE_C;
		break;

	case L1_BRICKTYPE_PX:
	case L1_BRICKTYPE_PE:
	case L1_BRICKTYPE_PA:
	case L1_BRICKTYPE_SA: /* we can move this to the "I's" later
			       * if that makes more sense
			       */
		brickchar = L1_BRICKTYPE_P;
		break;

	case L1_BRICKTYPE_IX:
	case L1_BRICKTYPE_IA:

		brickchar = L1_BRICKTYPE_I;
		break;
	}

	position = MODULE_GET_BPOS(m);

	if ((fmt == MODULE_FORMAT_BRIEF) || (fmt == MODULE_FORMAT_LCD)) {
		/* Brief module number format, eg. 002c15 */

		/* Decompress the rack number */
		*buffer++ = '0' + RACK_GET_CLASS(rack);
		*buffer++ = '0' + RACK_GET_GROUP(rack);
		*buffer++ = '0' + RACK_GET_NUM(rack);

		/* Add the brick type */
		*buffer++ = brickchar;
	}
	else if (fmt == MODULE_FORMAT_LONG) {
		/* Fuller hwgraph format, eg. rack/002/bay/15 */

		strcpy(buffer, "rack" "/");  buffer += strlen(buffer);

		*buffer++ = '0' + RACK_GET_CLASS(rack);
		*buffer++ = '0' + RACK_GET_GROUP(rack);
		*buffer++ = '0' + RACK_GET_NUM(rack);

		strcpy(buffer, "/" "bay" "/");  buffer += strlen(buffer);
	}

	/* Add the bay position, using at least two digits */
	if (position < 10)
		*buffer++ = '0';
	sprintf(buffer, "%d", position);
}