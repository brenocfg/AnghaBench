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
struct tls_scmd {int /*<<< orphan*/  seqno_numivs; } ;
struct sock {int dummy; } ;
struct chtls_hws {int mfs; struct tls_scmd scmd; } ;
struct chtls_sock {struct chtls_hws tlshws; } ;

/* Variables and functions */
 int AEAD_EXPLICIT_DATA_SIZE ; 
 int GCM_TAG_SIZE ; 
 scalar_t__ SCMD_CIPH_MODE_AES_GCM ; 
 scalar_t__ SCMD_CIPH_MODE_G (int /*<<< orphan*/ ) ; 
 int TLS_HEADER_LENGTH ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 

__attribute__((used)) static int chtls_expansion_size(struct sock *sk, int data_len,
				int fullpdu,
				unsigned short *pducnt)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct chtls_hws *hws = &csk->tlshws;
	struct tls_scmd *scmd = &hws->scmd;
	int fragsize = hws->mfs;
	int expnsize = 0;
	int fragleft;
	int fragcnt;
	int expppdu;

	if (SCMD_CIPH_MODE_G(scmd->seqno_numivs) ==
	    SCMD_CIPH_MODE_AES_GCM) {
		expppdu = GCM_TAG_SIZE + AEAD_EXPLICIT_DATA_SIZE +
			  TLS_HEADER_LENGTH;

		if (fullpdu) {
			*pducnt = data_len / (expppdu + fragsize);
			if (*pducnt > 32)
				*pducnt = 32;
			else if (!*pducnt)
				*pducnt = 1;
			expnsize = (*pducnt) * expppdu;
			return expnsize;
		}
		fragcnt = (data_len / fragsize);
		expnsize =  fragcnt * expppdu;
		fragleft = data_len % fragsize;
		if (fragleft > 0)
			expnsize += expppdu;
	}
	return expnsize;
}