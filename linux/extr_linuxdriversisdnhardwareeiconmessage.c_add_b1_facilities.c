#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_8__ {long requested_options_conn; long requested_options; int Id; TYPE_2__* adapter; TYPE_1__* appl; } ;
struct TYPE_7__ {long* requested_options_table; int manufacturer_features; int /*<<< orphan*/  Id; } ;
struct TYPE_6__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 int B1_FACILITY_DTMFR ; 
 int B1_FACILITY_DTMFX ; 
 int B1_FACILITY_EC ; 
 int B1_FACILITY_LOCAL ; 
 int B1_FACILITY_MIXER ; 
 int B1_FACILITY_VOICE ; 
 scalar_t__ FILE_ ; 
 int MANUFACTURER_FEATURE_HARDDTMF ; 
 int MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE ; 
 int MANUFACTURER_FEATURE_SOFTDTMF_SEND ; 
 long PRIVATE_DTMF_TONE ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_b1_facilities (TYPE_3__*,int) ; 

__attribute__((used)) static byte add_b1_facilities(PLCI *plci, byte b1_resource, word b1_facilities)
{
	byte b;

	switch (b1_resource)
	{
	case 5:
	case 26:
		if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
			b = 26;
		else
			b = 5;
		break;

	case 8:
	case 27:
		if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
			b = 27;
		else
			b = 8;
		break;

	case 9:
	case 20:
	case 22:
	case 23:
	case 24:
	case 25:
	case 28:
	case 29:
	case 30:
	case 36:
	case 37:
	case 38:
		if (b1_facilities & B1_FACILITY_EC)
		{
			if (b1_facilities & B1_FACILITY_LOCAL)
				b = 30;
			else if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
				b = 29;
			else
				b = 28;
		}

		else if ((b1_facilities & (B1_FACILITY_DTMFX | B1_FACILITY_DTMFR | B1_FACILITY_MIXER))
			 && (((plci->requested_options_conn | plci->requested_options) & (1L << PRIVATE_DTMF_TONE))
			     || (plci->appl && (plci->adapter->requested_options_table[plci->appl->Id - 1] & (1L << PRIVATE_DTMF_TONE)))))
		{
			if (b1_facilities & B1_FACILITY_LOCAL)
				b = 38;
			else if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
				b = 37;
			else
				b = 36;
		}

		else if (((plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_HARDDTMF)
			  && !(plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE))
			 || ((b1_facilities & B1_FACILITY_DTMFR)
			     && ((b1_facilities & B1_FACILITY_MIXER)
				 || !(plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE)))
			 || ((b1_facilities & B1_FACILITY_DTMFX)
			     && ((b1_facilities & B1_FACILITY_MIXER)
				 || !(plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_SOFTDTMF_SEND))))
		{
			if (b1_facilities & B1_FACILITY_LOCAL)
				b = 24;
			else if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
				b = 23;
			else
				b = 22;
		}
		else
		{
			if (b1_facilities & B1_FACILITY_LOCAL)
				b = 25;
			else if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
				b = 20;
			else
				b = 9;
		}
		break;

	case 31:
	case 32:
	case 33:
		if (b1_facilities & B1_FACILITY_LOCAL)
			b = 33;
		else if (b1_facilities & (B1_FACILITY_MIXER | B1_FACILITY_VOICE))
			b = 32;
		else
			b = 31;
		break;

	default:
		b = b1_resource;
	}
	dbug(1, dprintf("[%06lx] %s,%d: add_b1_facilities %d %04x %d %04x",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__,
			b1_resource, b1_facilities, b, get_b1_facilities(plci, b)));
	return (b);
}