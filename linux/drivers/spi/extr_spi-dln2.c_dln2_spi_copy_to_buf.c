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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int dln2_spi_copy_to_buf(u8 *dln2_buf, const u8 *src, u16 len, u8 bpw)
{
#ifdef __LITTLE_ENDIAN
	memcpy(dln2_buf, src, len);
#else
	if (bpw <= 8) {
		memcpy(dln2_buf, src, len);
	} else if (bpw <= 16) {
		__le16 *d = (__le16 *)dln2_buf;
		u16 *s = (u16 *)src;

		len = len / 2;
		while (len--)
			*d++ = cpu_to_le16p(s++);
	} else {
		__le32 *d = (__le32 *)dln2_buf;
		u32 *s = (u32 *)src;

		len = len / 4;
		while (len--)
			*d++ = cpu_to_le32p(s++);
	}
#endif

	return 0;
}