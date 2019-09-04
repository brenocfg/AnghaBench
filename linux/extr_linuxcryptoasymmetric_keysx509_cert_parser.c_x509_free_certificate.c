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
struct x509_certificate {struct x509_certificate* skid; struct x509_certificate* id; struct x509_certificate* subject; struct x509_certificate* issuer; int /*<<< orphan*/  sig; int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct x509_certificate*) ; 
 int /*<<< orphan*/  public_key_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  public_key_signature_free (int /*<<< orphan*/ ) ; 

void x509_free_certificate(struct x509_certificate *cert)
{
	if (cert) {
		public_key_free(cert->pub);
		public_key_signature_free(cert->sig);
		kfree(cert->issuer);
		kfree(cert->subject);
		kfree(cert->id);
		kfree(cert->skid);
		kfree(cert);
	}
}