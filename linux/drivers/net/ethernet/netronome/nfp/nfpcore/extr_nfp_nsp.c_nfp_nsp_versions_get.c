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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  enum nfp_nsp_versions { ____Placeholder_nfp_nsp_versions } nfp_nsp_versions ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  NFP_VERSIONS_APP 141 
#define  NFP_VERSIONS_APP_OFF 140 
#define  NFP_VERSIONS_BSP 139 
#define  NFP_VERSIONS_BSP_OFF 138 
#define  NFP_VERSIONS_BUNDLE 137 
#define  NFP_VERSIONS_BUNDLE_OFF 136 
#define  NFP_VERSIONS_CFGR 135 
#define  NFP_VERSIONS_CFGR_OFF 134 
#define  NFP_VERSIONS_CPLD 133 
#define  NFP_VERSIONS_CPLD_OFF 132 
#define  NFP_VERSIONS_NCSI 131 
#define  NFP_VERSIONS_NCSI_OFF 130 
#define  NFP_VERSIONS_UNDI 129 
#define  NFP_VERSIONS_UNDI_OFF 128 
 unsigned int get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 unsigned int strnlen (int /*<<< orphan*/  const*,unsigned int) ; 

const char *nfp_nsp_versions_get(enum nfp_nsp_versions id, bool flash,
				 const u8 *buf, unsigned int size)
{
	static const u32 id2off[] = {
		[NFP_VERSIONS_BSP] =	NFP_VERSIONS_BSP_OFF,
		[NFP_VERSIONS_CPLD] =	NFP_VERSIONS_CPLD_OFF,
		[NFP_VERSIONS_APP] =	NFP_VERSIONS_APP_OFF,
		[NFP_VERSIONS_BUNDLE] =	NFP_VERSIONS_BUNDLE_OFF,
		[NFP_VERSIONS_UNDI] =	NFP_VERSIONS_UNDI_OFF,
		[NFP_VERSIONS_NCSI] =	NFP_VERSIONS_NCSI_OFF,
		[NFP_VERSIONS_CFGR] =	NFP_VERSIONS_CFGR_OFF,
	};
	unsigned int field, buf_field_cnt, buf_off;

	if (id >= ARRAY_SIZE(id2off) || !id2off[id])
		return ERR_PTR(-EINVAL);

	field = id * 2 + flash;

	buf_field_cnt = get_unaligned_le16(buf);
	if (buf_field_cnt <= field)
		return ERR_PTR(-ENOENT);

	buf_off = get_unaligned_le16(buf + id2off[id] + flash * 2);
	if (!buf_off)
		return ERR_PTR(-ENOENT);

	if (buf_off >= size)
		return ERR_PTR(-EINVAL);
	if (strnlen(&buf[buf_off], size - buf_off) == size - buf_off)
		return ERR_PTR(-EINVAL);

	return (const char *)&buf[buf_off];
}