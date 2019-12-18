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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct t10_pr_registration {unsigned char* pr_reg_isid; scalar_t__ isid_present_at_reg; } ;
struct se_node_acl {char* initiatorname; int /*<<< orphan*/  nacl_sess_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be16 (size_t,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 size_t sprintf (unsigned char*,char*,char*) ; 

__attribute__((used)) static int iscsi_get_pr_transport_id(
	struct se_node_acl *se_nacl,
	struct t10_pr_registration *pr_reg,
	int *format_code,
	unsigned char *buf)
{
	u32 off = 4, padding = 0;
	u16 len = 0;

	spin_lock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * From spc4r17 Section 7.5.4.6: TransportID for initiator
	 * ports using SCSI over iSCSI.
	 *
	 * The null-terminated, null-padded (see 4.4.2) ISCSI NAME field
	 * shall contain the iSCSI name of an iSCSI initiator node (see
	 * RFC 3720). The first ISCSI NAME field byte containing an ASCII
	 * null character terminates the ISCSI NAME field without regard for
	 * the specified length of the iSCSI TransportID or the contents of
	 * the ADDITIONAL LENGTH field.
	 */
	len = sprintf(&buf[off], "%s", se_nacl->initiatorname);
	/*
	 * Add Extra byte for NULL terminator
	 */
	len++;
	/*
	 * If there is ISID present with the registration and *format code == 1
	 * 1, use iSCSI Initiator port TransportID format.
	 *
	 * Otherwise use iSCSI Initiator device TransportID format that
	 * does not contain the ASCII encoded iSCSI Initiator iSID value
	 * provied by the iSCSi Initiator during the iSCSI login process.
	 */
	if ((*format_code == 1) && (pr_reg->isid_present_at_reg)) {
		/*
		 * Set FORMAT CODE 01b for iSCSI Initiator port TransportID
		 * format.
		 */
		buf[0] |= 0x40;
		/*
		 * From spc4r17 Section 7.5.4.6: TransportID for initiator
		 * ports using SCSI over iSCSI.  Table 390
		 *
		 * The SEPARATOR field shall contain the five ASCII
		 * characters ",i,0x".
		 *
		 * The null-terminated, null-padded ISCSI INITIATOR SESSION ID
		 * field shall contain the iSCSI initiator session identifier
		 * (see RFC 3720) in the form of ASCII characters that are the
		 * hexadecimal digits converted from the binary iSCSI initiator
		 * session identifier value. The first ISCSI INITIATOR SESSION
		 * ID field byte containing an ASCII null character
		 */
		buf[off+len] = 0x2c; off++; /* ASCII Character: "," */
		buf[off+len] = 0x69; off++; /* ASCII Character: "i" */
		buf[off+len] = 0x2c; off++; /* ASCII Character: "," */
		buf[off+len] = 0x30; off++; /* ASCII Character: "0" */
		buf[off+len] = 0x78; off++; /* ASCII Character: "x" */
		len += 5;
		buf[off+len] = pr_reg->pr_reg_isid[0]; off++;
		buf[off+len] = pr_reg->pr_reg_isid[1]; off++;
		buf[off+len] = pr_reg->pr_reg_isid[2]; off++;
		buf[off+len] = pr_reg->pr_reg_isid[3]; off++;
		buf[off+len] = pr_reg->pr_reg_isid[4]; off++;
		buf[off+len] = pr_reg->pr_reg_isid[5]; off++;
		buf[off+len] = '\0'; off++;
		len += 7;
	}
	spin_unlock_irq(&se_nacl->nacl_sess_lock);
	/*
	 * The ADDITIONAL LENGTH field specifies the number of bytes that follow
	 * in the TransportID. The additional length shall be at least 20 and
	 * shall be a multiple of four.
	*/
	padding = ((-len) & 3);
	if (padding != 0)
		len += padding;

	put_unaligned_be16(len, &buf[2]);
	/*
	 * Increment value for total payload + header length for
	 * full status descriptor
	 */
	len += 4;

	return len;
}