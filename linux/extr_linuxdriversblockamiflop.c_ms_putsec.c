#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; int member_16; int member_17; int member_18; int member_19; int member_20; int member_21; } ;
struct dos_header {int member_3; int track; int side; int sec; int /*<<< orphan*/  crc; TYPE_1__ member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int track; scalar_t__ trackbuf; TYPE_2__* type; } ;
struct TYPE_5__ {int heads; } ;

/* Variables and functions */
 int dos_data_crc (scalar_t__) ; 
 int /*<<< orphan*/  dos_encode_block (int*,unsigned char*,int) ; 
 int /*<<< orphan*/  dos_hdr_crc (struct dos_header*) ; 
 TYPE_3__* unit ; 

__attribute__((used)) static unsigned long *ms_putsec(int drive, unsigned long *raw, int cnt)
{
	static struct dos_header hdr={0,0,0,2,0,
	  {78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78}};
	int i;
	static ushort crc[2]={0,0x4e4e};

	drive&=3;
/* id gap 1 */
/* the MFM word before is always 9254 */
	for(i=0;i<6;i++)
		*raw++=0xaaaaaaaa;
/* 3 sync + 1 headermark */
	*raw++=0x44894489;
	*raw++=0x44895554;

/* fill in the variable parts of the header */
	hdr.track=unit[drive].track/unit[drive].type->heads;
	hdr.side=unit[drive].track%unit[drive].type->heads;
	hdr.sec=cnt+1;
	hdr.crc=dos_hdr_crc(&hdr);

/* header (without "magic") and id gap 2*/
	dos_encode_block((ushort *)raw,(unsigned char *) &hdr.track,28);
	raw+=14;

/*id gap 3 */
	for(i=0;i<6;i++)
		*raw++=0xaaaaaaaa;

/* 3 syncs and 1 datamark */
	*raw++=0x44894489;
	*raw++=0x44895545;

/* data */
	dos_encode_block((ushort *)raw,
			 (unsigned char *)unit[drive].trackbuf+cnt*512,512);
	raw+=256;

/*data crc + jd's special gap (long words :-/) */
	crc[0]=dos_data_crc(unit[drive].trackbuf+cnt*512);
	dos_encode_block((ushort *) raw,(unsigned char *)crc,4);
	raw+=2;

/* data gap */
	for(i=0;i<38;i++)
		*raw++=0x92549254;

	return raw; /* wrote 652 MFM words */
}