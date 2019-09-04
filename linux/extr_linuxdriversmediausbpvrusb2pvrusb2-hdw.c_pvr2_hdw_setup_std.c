#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct TYPE_8__ {int valid_bits; } ;
struct TYPE_9__ {TYPE_2__ type_bitmask; } ;
struct TYPE_10__ {TYPE_3__ def; } ;
struct pvr2_hdw {int std_mask_eeprom; int std_mask_avail; int std_mask_cur; int std_dirty; TYPE_4__ std_info_cur; TYPE_1__* hdw_desc; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {int msk; int pat; int std; } ;
struct TYPE_7__ {int default_std_mask; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  PVR2_TRACE_STD ; 
 int get_default_standard (struct pvr2_hdw*) ; 
 unsigned int pvr2_std_id_to_str (char*,int,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 TYPE_5__* std_eeprom_maps ; 

__attribute__((used)) static void pvr2_hdw_setup_std(struct pvr2_hdw *hdw)
{
	char buf[40];
	unsigned int bcnt;
	v4l2_std_id std1,std2,std3;

	std1 = get_default_standard(hdw);
	std3 = std1 ? 0 : hdw->hdw_desc->default_std_mask;

	bcnt = pvr2_std_id_to_str(buf,sizeof(buf),hdw->std_mask_eeprom);
	pvr2_trace(PVR2_TRACE_STD,
		   "Supported video standard(s) reported available in hardware: %.*s",
		   bcnt,buf);

	hdw->std_mask_avail = hdw->std_mask_eeprom;

	std2 = (std1|std3) & ~hdw->std_mask_avail;
	if (std2) {
		bcnt = pvr2_std_id_to_str(buf,sizeof(buf),std2);
		pvr2_trace(PVR2_TRACE_STD,
			   "Expanding supported video standards to include: %.*s",
			   bcnt,buf);
		hdw->std_mask_avail |= std2;
	}

	hdw->std_info_cur.def.type_bitmask.valid_bits = hdw->std_mask_avail;

	if (std1) {
		bcnt = pvr2_std_id_to_str(buf,sizeof(buf),std1);
		pvr2_trace(PVR2_TRACE_STD,
			   "Initial video standard forced to %.*s",
			   bcnt,buf);
		hdw->std_mask_cur = std1;
		hdw->std_dirty = !0;
		return;
	}
	if (std3) {
		bcnt = pvr2_std_id_to_str(buf,sizeof(buf),std3);
		pvr2_trace(PVR2_TRACE_STD,
			   "Initial video standard (determined by device type): %.*s",
			   bcnt, buf);
		hdw->std_mask_cur = std3;
		hdw->std_dirty = !0;
		return;
	}

	{
		unsigned int idx;
		for (idx = 0; idx < ARRAY_SIZE(std_eeprom_maps); idx++) {
			if (std_eeprom_maps[idx].msk ?
			    ((std_eeprom_maps[idx].pat ^
			     hdw->std_mask_eeprom) &
			     std_eeprom_maps[idx].msk) :
			    (std_eeprom_maps[idx].pat !=
			     hdw->std_mask_eeprom)) continue;
			bcnt = pvr2_std_id_to_str(buf,sizeof(buf),
						  std_eeprom_maps[idx].std);
			pvr2_trace(PVR2_TRACE_STD,
				   "Initial video standard guessed as %.*s",
				   bcnt,buf);
			hdw->std_mask_cur = std_eeprom_maps[idx].std;
			hdw->std_dirty = !0;
			return;
		}
	}

}