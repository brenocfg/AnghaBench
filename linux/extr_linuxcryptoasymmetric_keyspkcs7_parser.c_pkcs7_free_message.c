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
struct x509_certificate {struct x509_certificate* next; } ;
struct pkcs7_signed_info {struct pkcs7_signed_info* next; } ;
struct pkcs7_message {struct pkcs7_signed_info* signed_infos; struct x509_certificate* crl; struct x509_certificate* certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pkcs7_message*) ; 
 int /*<<< orphan*/  pkcs7_free_signed_info (struct pkcs7_signed_info*) ; 
 int /*<<< orphan*/  x509_free_certificate (struct x509_certificate*) ; 

void pkcs7_free_message(struct pkcs7_message *pkcs7)
{
	struct x509_certificate *cert;
	struct pkcs7_signed_info *sinfo;

	if (pkcs7) {
		while (pkcs7->certs) {
			cert = pkcs7->certs;
			pkcs7->certs = cert->next;
			x509_free_certificate(cert);
		}
		while (pkcs7->crl) {
			cert = pkcs7->crl;
			pkcs7->crl = cert->next;
			x509_free_certificate(cert);
		}
		while (pkcs7->signed_infos) {
			sinfo = pkcs7->signed_infos;
			pkcs7->signed_infos = sinfo->next;
			pkcs7_free_signed_info(sinfo);
		}
		kfree(pkcs7);
	}
}