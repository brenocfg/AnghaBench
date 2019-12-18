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

/* Variables and functions */
 unsigned char* GetAddr1Ptr (unsigned char*) ; 
 unsigned char* GetAddr2Ptr (unsigned char*) ; 
 unsigned char* GetAddr3Ptr (unsigned char*) ; 
 int GetFrDs (unsigned char*) ; 
 int GetToDs (unsigned char*) ; 

__attribute__((used)) static inline unsigned char *get_hdr_bssid(unsigned char *pframe)
{
	unsigned char	*sa;
	unsigned int	to_fr_ds = (GetToDs(pframe) << 1) | GetFrDs(pframe);

	switch (to_fr_ds) {
	case 0x00:	/* ToDs=0, FromDs=0 */
		sa = GetAddr3Ptr(pframe);
		break;
	case 0x01:	/* ToDs=0, FromDs=1 */
		sa = GetAddr2Ptr(pframe);
		break;
	case 0x02:	/* ToDs=1, FromDs=0 */
		sa = GetAddr1Ptr(pframe);
		break;
	default:	/* ToDs=1, FromDs=1 */
		sa = NULL;
		break;
	}
	return sa;
}